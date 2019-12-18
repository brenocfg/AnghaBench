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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CF8305_CARDID ; 
 scalar_t__ CF8305_MANFID ; 
 scalar_t__ CF8381_CARDID ; 
 scalar_t__ CF8381_MANFID ; 
 scalar_t__ CF8385_CARDID ; 
 scalar_t__ CF8385_MANFID ; 
 int /*<<< orphan*/  MODEL_8305 ; 
 int /*<<< orphan*/  MODEL_8381 ; 
 int /*<<< orphan*/  MODEL_8385 ; 
 int /*<<< orphan*/  MODEL_UNKNOWN ; 

__attribute__((used)) static inline u32 get_model(u16 manf_id, u16 card_id)
{
	/* NOTE: keep in sync with if_cs_ids */
	if (manf_id == CF8305_MANFID && card_id == CF8305_CARDID)
		return MODEL_8305;
	else if (manf_id == CF8381_MANFID && card_id == CF8381_CARDID)
		return MODEL_8381;
	else if (manf_id == CF8385_MANFID && card_id == CF8385_CARDID)
		return MODEL_8385;
	return MODEL_UNKNOWN;
}