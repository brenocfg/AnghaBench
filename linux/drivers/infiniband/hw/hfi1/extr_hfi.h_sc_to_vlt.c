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
typedef  scalar_t__ u8 ;
struct hfi1_devdata {scalar_t__ sc2vl; int /*<<< orphan*/  sc2vl_lock; } ;

/* Variables and functions */
 scalar_t__ OPA_MAX_SCS ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline u8 sc_to_vlt(struct hfi1_devdata *dd, u8 sc5)
{
	unsigned seq;
	u8 rval;

	if (sc5 >= OPA_MAX_SCS)
		return (u8)(0xff);

	do {
		seq = read_seqbegin(&dd->sc2vl_lock);
		rval = *(((u8 *)dd->sc2vl) + sc5);
	} while (read_seqretry(&dd->sc2vl_lock, seq));

	return rval;
}