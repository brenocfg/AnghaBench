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
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 scalar_t__ RXE_MAX_HDR_LENGTH ; 
 int rxe_mtu_int_to_enum (int) ; 

__attribute__((used)) static inline enum ib_mtu eth_mtu_int_to_enum(int mtu)
{
	mtu -= RXE_MAX_HDR_LENGTH;

	return rxe_mtu_int_to_enum(mtu);
}