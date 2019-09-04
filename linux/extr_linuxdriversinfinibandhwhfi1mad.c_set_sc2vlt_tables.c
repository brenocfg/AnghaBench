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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int /*<<< orphan*/  sc2vl_lock; int /*<<< orphan*/  sc2vl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SC2VLT0 ; 
 int /*<<< orphan*/  SEND_SC2VLT1 ; 
 int /*<<< orphan*/  SEND_SC2VLT2 ; 
 int /*<<< orphan*/  SEND_SC2VLT3 ; 
 int /*<<< orphan*/  filter_sc2vlt (void*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_sc2vlt_tables(struct hfi1_devdata *dd, void *data)
{
	u64 *val = data;

	filter_sc2vlt(data, true);

	write_csr(dd, SEND_SC2VLT0, *val++);
	write_csr(dd, SEND_SC2VLT1, *val++);
	write_csr(dd, SEND_SC2VLT2, *val++);
	write_csr(dd, SEND_SC2VLT3, *val++);
	write_seqlock_irq(&dd->sc2vl_lock);
	memcpy(dd->sc2vl, data, sizeof(dd->sc2vl));
	write_sequnlock_irq(&dd->sc2vl_lock);
	return 0;
}