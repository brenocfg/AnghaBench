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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPP_DFIFO_RD0 ; 
 int /*<<< orphan*/  IPP_DFIFO_RD1 ; 
 int /*<<< orphan*/  IPP_DFIFO_RD2 ; 
 int /*<<< orphan*/  IPP_DFIFO_RD3 ; 
 int /*<<< orphan*/  IPP_DFIFO_RD4 ; 
 int /*<<< orphan*/  IPP_DFIFO_RD_PTR ; 
 int /*<<< orphan*/  nr64_ipp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_ipp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_ipp_read(struct niu *np, int index, u64 *data)
{
	nw64_ipp(IPP_DFIFO_RD_PTR, index);
	data[0] = nr64_ipp(IPP_DFIFO_RD0);
	data[1] = nr64_ipp(IPP_DFIFO_RD1);
	data[2] = nr64_ipp(IPP_DFIFO_RD2);
	data[3] = nr64_ipp(IPP_DFIFO_RD3);
	data[4] = nr64_ipp(IPP_DFIFO_RD4);
}