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
struct cx18_card {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct cx18_card const**) ; 
 struct cx18_card const** cx18_card_list ; 

const struct cx18_card *cx18_get_card(u16 index)
{
	if (index >= ARRAY_SIZE(cx18_card_list))
		return NULL;
	return cx18_card_list[index];
}