#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_cuir_message {scalar_t__ code; int /*<<< orphan*/  message_id; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* check_attention ) (struct dasd_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CUIR_QUIESCE ; 
 scalar_t__ CUIR_RESUME ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int PSF_CUIR_COMPLETED ; 
 int PSF_CUIR_LAST_PATH ; 
 int PSF_CUIR_NOT_SUPPORTED ; 
 scalar_t__ dasd_eckd_cuir_quiesce (struct dasd_device*,int /*<<< orphan*/ ,struct dasd_cuir_message*) ; 
 int /*<<< orphan*/  dasd_eckd_cuir_resume (struct dasd_device*,int /*<<< orphan*/ ,struct dasd_cuir_message*) ; 
 int /*<<< orphan*/  dasd_eckd_psf_cuir_response (struct dasd_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dasd_eckd_handle_cuir(struct dasd_device *device, void *messages,
				 __u8 lpum)
{
	struct dasd_cuir_message *cuir = messages;
	int response;

	DBF_DEV_EVENT(DBF_WARNING, device,
		      "CUIR request: %016llx %016llx %016llx %08x",
		      ((u64 *)cuir)[0], ((u64 *)cuir)[1], ((u64 *)cuir)[2],
		      ((u32 *)cuir)[3]);

	if (cuir->code == CUIR_QUIESCE) {
		/* quiesce */
		if (dasd_eckd_cuir_quiesce(device, lpum, cuir))
			response = PSF_CUIR_LAST_PATH;
		else
			response = PSF_CUIR_COMPLETED;
	} else if (cuir->code == CUIR_RESUME) {
		/* resume */
		dasd_eckd_cuir_resume(device, lpum, cuir);
		response = PSF_CUIR_COMPLETED;
	} else
		response = PSF_CUIR_NOT_SUPPORTED;

	dasd_eckd_psf_cuir_response(device, response,
				    cuir->message_id, lpum);
	DBF_DEV_EVENT(DBF_WARNING, device,
		      "CUIR response: %d on message ID %08x", response,
		      cuir->message_id);
	/* to make sure there is no attention left schedule work again */
	device->discipline->check_attention(device, lpum);
}