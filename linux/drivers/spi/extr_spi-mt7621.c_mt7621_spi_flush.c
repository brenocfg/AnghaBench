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
struct mt7621_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7621_spi_read_half_duplex (struct mt7621_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mt7621_spi_flush(struct mt7621_spi *rs)
{
	mt7621_spi_read_half_duplex(rs, 0, NULL);
}