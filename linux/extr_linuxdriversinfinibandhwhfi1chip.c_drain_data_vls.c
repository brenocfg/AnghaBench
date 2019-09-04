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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pause_for_credit_return (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  sc_wait (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  sdma_wait (struct hfi1_devdata*) ; 

__attribute__((used)) static void drain_data_vls(struct hfi1_devdata *dd)
{
	sc_wait(dd);
	sdma_wait(dd);
	pause_for_credit_return(dd);
}