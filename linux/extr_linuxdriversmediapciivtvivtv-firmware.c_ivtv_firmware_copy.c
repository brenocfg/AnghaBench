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
struct ivtv {int /*<<< orphan*/  dec_mem; int /*<<< orphan*/  has_cx23415; int /*<<< orphan*/  enc_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_FIRM_DEC_FILENAME ; 
 int /*<<< orphan*/  CX2341X_FIRM_ENC_FILENAME ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
 scalar_t__ IVTV_FW_DEC_SIZE ; 
 scalar_t__ IVTV_FW_ENC_SIZE ; 
 scalar_t__ load_fw_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ivtv*,scalar_t__) ; 

__attribute__((used)) static int ivtv_firmware_copy(struct ivtv *itv)
{
	IVTV_DEBUG_INFO("Loading encoder image\n");
	if (load_fw_direct(CX2341X_FIRM_ENC_FILENAME,
		   itv->enc_mem, itv, IVTV_FW_ENC_SIZE) != IVTV_FW_ENC_SIZE) {
		IVTV_DEBUG_WARN("failed loading encoder firmware\n");
		return -3;
	}
	if (!itv->has_cx23415)
		return 0;

	IVTV_DEBUG_INFO("Loading decoder image\n");
	if (load_fw_direct(CX2341X_FIRM_DEC_FILENAME,
		   itv->dec_mem, itv, IVTV_FW_DEC_SIZE) != IVTV_FW_DEC_SIZE) {
		IVTV_DEBUG_WARN("failed loading decoder firmware\n");
		return -1;
	}
	return 0;
}