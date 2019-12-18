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
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sun6i_dsi_crc_compute (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u16 sun6i_dsi_crc_repeat(u8 pd, u8 *buffer, size_t len)
{
	memset(buffer, pd, len);

	return sun6i_dsi_crc_compute(buffer, len);
}