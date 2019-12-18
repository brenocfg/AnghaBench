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
struct brcmf_sdio {scalar_t__ tx_seq; scalar_t__ tx_max; } ;

/* Variables and functions */

__attribute__((used)) static bool data_ok(struct brcmf_sdio *bus)
{
	return (u8)(bus->tx_max - bus->tx_seq) != 0 &&
	       ((u8)(bus->tx_max - bus->tx_seq) & 0x80) == 0;
}