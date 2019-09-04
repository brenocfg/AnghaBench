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
struct RxD_t {int Control_1; int /*<<< orphan*/  Control_2; } ;

/* Variables and functions */
 scalar_t__ GET_RXD_MARKER (int /*<<< orphan*/ ) ; 
 int RXD_OWN_XENA ; 
 scalar_t__ THE_RXD_MARK ; 

__attribute__((used)) static inline int RXD_IS_UP2DT(struct RxD_t *rxdp)
{
	int ret;

	ret = ((!(rxdp->Control_1 & RXD_OWN_XENA)) &&
	       (GET_RXD_MARKER(rxdp->Control_2) != THE_RXD_MARK));

	return ret;
}