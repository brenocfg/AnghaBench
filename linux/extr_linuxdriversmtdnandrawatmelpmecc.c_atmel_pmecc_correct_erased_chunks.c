#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atmel_pmecc_user {TYPE_2__* pmecc; } ;
struct TYPE_4__ {TYPE_1__* caps; } ;
struct TYPE_3__ {int correct_erased_chunks; } ;

/* Variables and functions */

bool atmel_pmecc_correct_erased_chunks(struct atmel_pmecc_user *user)
{
	return user->pmecc->caps->correct_erased_chunks;
}