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
typedef  int /*<<< orphan*/  u32 ;
struct intel_guc_ct_channel {int dummy; } ;
struct intel_guc_ct {struct intel_guc_ct_channel host_channel; } ;
struct intel_guc {int /*<<< orphan*/  send_mutex; struct intel_guc_ct ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG_DRIVER (char*,int /*<<< orphan*/  const,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 
 int ctch_send (struct intel_guc_ct*,struct intel_guc_ct_channel*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int intel_guc_send_ct(struct intel_guc *guc, const u32 *action, u32 len,
		      u32 *response_buf, u32 response_buf_size)
{
	struct intel_guc_ct *ct = &guc->ct;
	struct intel_guc_ct_channel *ctch = &ct->host_channel;
	u32 status = ~0; /* undefined */
	int ret;

	mutex_lock(&guc->send_mutex);

	ret = ctch_send(ct, ctch, action, len, response_buf, response_buf_size,
			&status);
	if (unlikely(ret < 0)) {
		DRM_ERROR("CT: send action %#X failed; err=%d status=%#X\n",
			  action[0], ret, status);
	} else if (unlikely(ret)) {
		CT_DEBUG_DRIVER("CT: send action %#x returned %d (%#x)\n",
				action[0], ret, ret);
	}

	mutex_unlock(&guc->send_mutex);
	return ret;
}