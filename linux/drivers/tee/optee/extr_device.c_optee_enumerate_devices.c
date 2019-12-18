#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct tee_shm {int /*<<< orphan*/  b; } const tee_shm ;
typedef  struct tee_shm uuid_t ;
typedef  int u32 ;
struct tee_ioctl_open_session_arg {scalar_t__ ret; int /*<<< orphan*/  session; scalar_t__ num_params; int /*<<< orphan*/  clnt_login; int /*<<< orphan*/  uuid; } ;
typedef  struct tee_context {int /*<<< orphan*/  b; } const tee_context ;
typedef  int /*<<< orphan*/  sess_arg ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct tee_shm const*) ; 
 int PTR_ERR (struct tee_shm const*) ; 
 scalar_t__ TEEC_SUCCESS ; 
 int /*<<< orphan*/  TEE_IOCTL_LOGIN_PUBLIC ; 
 int /*<<< orphan*/  TEE_IOCTL_UUID_LEN ; 
 int TEE_SHM_DMA_BUF ; 
 int TEE_SHM_MAPPED ; 
 struct tee_shm UUID_INIT (int,int,int,int,int,int,int,int,int,int,int) ; 
 int get_devices (struct tee_shm const*,int /*<<< orphan*/ ,struct tee_shm const*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tee_ioctl_open_session_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optee_ctx_match ; 
 int optee_register_device (struct tee_shm const*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tee_client_close_context (struct tee_shm const*) ; 
 int /*<<< orphan*/  tee_client_close_session (struct tee_shm const*,int /*<<< orphan*/ ) ; 
 struct tee_shm* tee_client_open_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tee_client_open_session (struct tee_shm const*,struct tee_ioctl_open_session_arg*,int /*<<< orphan*/ *) ; 
 struct tee_shm* tee_shm_alloc (struct tee_shm const*,int,int) ; 
 int /*<<< orphan*/  tee_shm_free (struct tee_shm const*) ; 
 struct tee_shm* tee_shm_get_va (struct tee_shm const*,int /*<<< orphan*/ ) ; 

int optee_enumerate_devices(void)
{
	const uuid_t pta_uuid =
		UUID_INIT(0x7011a688, 0xddde, 0x4053,
			  0xa5, 0xa9, 0x7b, 0x3c, 0x4d, 0xdf, 0x13, 0xb8);
	struct tee_ioctl_open_session_arg sess_arg;
	struct tee_shm *device_shm = NULL;
	const uuid_t *device_uuid = NULL;
	struct tee_context *ctx = NULL;
	u32 shm_size = 0, idx, num_devices = 0;
	int rc;

	memset(&sess_arg, 0, sizeof(sess_arg));

	/* Open context with OP-TEE driver */
	ctx = tee_client_open_context(NULL, optee_ctx_match, NULL, NULL);
	if (IS_ERR(ctx))
		return -ENODEV;

	/* Open session with device enumeration pseudo TA */
	memcpy(sess_arg.uuid, pta_uuid.b, TEE_IOCTL_UUID_LEN);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	rc = tee_client_open_session(ctx, &sess_arg, NULL);
	if ((rc < 0) || (sess_arg.ret != TEEC_SUCCESS)) {
		/* Device enumeration pseudo TA not found */
		rc = 0;
		goto out_ctx;
	}

	rc = get_devices(ctx, sess_arg.session, NULL, &shm_size);
	if (rc < 0 || !shm_size)
		goto out_sess;

	device_shm = tee_shm_alloc(ctx, shm_size,
				   TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(device_shm)) {
		pr_err("tee_shm_alloc failed\n");
		rc = PTR_ERR(device_shm);
		goto out_sess;
	}

	rc = get_devices(ctx, sess_arg.session, device_shm, &shm_size);
	if (rc < 0)
		goto out_shm;

	device_uuid = tee_shm_get_va(device_shm, 0);
	if (IS_ERR(device_uuid)) {
		pr_err("tee_shm_get_va failed\n");
		rc = PTR_ERR(device_uuid);
		goto out_shm;
	}

	num_devices = shm_size / sizeof(uuid_t);

	for (idx = 0; idx < num_devices; idx++) {
		rc = optee_register_device(&device_uuid[idx], idx);
		if (rc)
			goto out_shm;
	}

out_shm:
	tee_shm_free(device_shm);
out_sess:
	tee_client_close_session(ctx, sess_arg.session);
out_ctx:
	tee_client_close_context(ctx);

	return rc;
}