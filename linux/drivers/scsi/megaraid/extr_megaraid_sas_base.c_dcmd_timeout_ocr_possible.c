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
struct megasas_instance {scalar_t__ adapter_type; int /*<<< orphan*/  reset_flags; scalar_t__ unload; } ;

/* Variables and functions */
 int IGNORE_TIMEOUT ; 
 int INITIATE_OCR ; 
 int KILL_ADAPTER ; 
 int /*<<< orphan*/  MEGASAS_FUSION_IN_RESET ; 
 scalar_t__ MFI_SERIES ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline int
dcmd_timeout_ocr_possible(struct megasas_instance *instance) {

	if (instance->adapter_type == MFI_SERIES)
		return KILL_ADAPTER;
	else if (instance->unload ||
			test_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags))
		return IGNORE_TIMEOUT;
	else
		return INITIATE_OCR;
}