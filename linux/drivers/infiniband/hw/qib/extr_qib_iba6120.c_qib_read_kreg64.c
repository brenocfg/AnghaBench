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
typedef  int u64 ;
typedef  size_t u16 ;
struct qib_devdata {int flags; int /*<<< orphan*/ * kregbase; } ;

/* Variables and functions */
 int QIB_PRESENT ; 
 int readq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u64 qib_read_kreg64(const struct qib_devdata *dd,
				  const u16 regno)
{
	if (!dd->kregbase || !(dd->flags & QIB_PRESENT))
		return -1;

	return readq(&dd->kregbase[regno]);
}