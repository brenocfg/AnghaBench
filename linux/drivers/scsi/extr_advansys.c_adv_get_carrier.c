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
typedef  int u32 ;
struct adv_dvc_var {int /*<<< orphan*/ * carrier; } ;
typedef  int /*<<< orphan*/  ADV_CARR_T ;

/* Variables and functions */
 int ADV_CARRIER_BUFSIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static ADV_CARR_T *adv_get_carrier(struct adv_dvc_var *adv_dvc, u32 offset)
{
	int index;

	BUG_ON(offset > ADV_CARRIER_BUFSIZE);

	index = offset / sizeof(ADV_CARR_T);
	return &adv_dvc->carrier[index];
}