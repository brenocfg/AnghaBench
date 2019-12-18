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
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_CM_GLOBAL_CREDIT ; 
 int SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SHIFT ; 
 int SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_global_shared(struct hfi1_devdata *dd, u16 limit)
{
	u64 reg;

	reg = read_csr(dd, SEND_CM_GLOBAL_CREDIT);
	reg &= ~SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK;
	reg |= (u64)limit << SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SHIFT;
	write_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);
}