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
typedef  int u16 ;

/* Variables and functions */
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 elants_i2c_parse_version(u8 *buf)
{
	return get_unaligned_be32(buf) >> 4;
}