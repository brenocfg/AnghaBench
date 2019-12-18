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
struct brcm_message {int type; } ;

/* Variables and functions */
#define  BRCM_MESSAGE_SBA 129 
#define  BRCM_MESSAGE_SPU 128 
 int flexrm_sba_sanity_check (struct brcm_message*) ; 
 int flexrm_spu_sanity_check (struct brcm_message*) ; 

__attribute__((used)) static bool flexrm_sanity_check(struct brcm_message *msg)
{
	if (!msg)
		return false;

	switch (msg->type) {
	case BRCM_MESSAGE_SPU:
		return flexrm_spu_sanity_check(msg);
	case BRCM_MESSAGE_SBA:
		return flexrm_sba_sanity_check(msg);
	default:
		return false;
	};
}