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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  crc_ccitt (int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static u16 sun6i_dsi_crc_compute(u8 const *buffer, size_t len)
{
	return crc_ccitt(0xffff, buffer, len);
}