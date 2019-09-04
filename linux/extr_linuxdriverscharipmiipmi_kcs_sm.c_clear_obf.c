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
struct si_sm_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_STATUS_OBF (unsigned char) ; 
 int /*<<< orphan*/  read_data (struct si_sm_data*) ; 

__attribute__((used)) static void clear_obf(struct si_sm_data *kcs, unsigned char status)
{
	if (GET_STATUS_OBF(status))
		read_data(kcs);
}