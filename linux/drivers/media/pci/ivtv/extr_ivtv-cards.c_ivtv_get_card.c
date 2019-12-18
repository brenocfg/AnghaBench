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
typedef  size_t u16 ;
struct ivtv_card {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct ivtv_card const**) ; 
 struct ivtv_card const** ivtv_card_list ; 

const struct ivtv_card *ivtv_get_card(u16 index)
{
	if (index >= ARRAY_SIZE(ivtv_card_list))
		return NULL;
	return ivtv_card_list[index];
}