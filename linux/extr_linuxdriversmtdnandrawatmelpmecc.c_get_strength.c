#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t cfg; } ;
struct atmel_pmecc_user {TYPE_3__ cache; TYPE_2__* pmecc; } ;
struct TYPE_5__ {TYPE_1__* caps; } ;
struct TYPE_4__ {int* strengths; } ;

/* Variables and functions */
 size_t PMECC_CFG_BCH_STRENGTH_MASK ; 

__attribute__((used)) static int get_strength(struct atmel_pmecc_user *user)
{
	const int *strengths = user->pmecc->caps->strengths;

	return strengths[user->cache.cfg & PMECC_CFG_BCH_STRENGTH_MASK];
}