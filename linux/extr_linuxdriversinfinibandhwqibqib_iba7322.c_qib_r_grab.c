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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SJA_EN ; 
 int /*<<< orphan*/  kr_r_access ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_r_grab(struct qib_devdata *dd)
{
	u64 val = SJA_EN;

	qib_write_kreg(dd, kr_r_access, val);
	qib_read_kreg32(dd, kr_scratch);
	return 0;
}