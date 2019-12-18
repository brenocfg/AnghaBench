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
typedef  int /*<<< orphan*/  nsp32_hw_data ;

/* Variables and functions */
 int nsp32_prom_read_bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp32_prom_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp32_prom_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp32_prom_write_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nsp32_prom_read(nsp32_hw_data *data, int romaddr)
{
	int i, val;

	/* start condition */
	nsp32_prom_start(data);

	/* device address */
	nsp32_prom_write_bit(data, 1);	/* 1 */
	nsp32_prom_write_bit(data, 0);	/* 0 */
	nsp32_prom_write_bit(data, 1);	/* 1 */
	nsp32_prom_write_bit(data, 0);	/* 0 */
	nsp32_prom_write_bit(data, 0);	/* A2: 0 (GND) */
	nsp32_prom_write_bit(data, 0);	/* A1: 0 (GND) */
	nsp32_prom_write_bit(data, 0);	/* A0: 0 (GND) */

	/* R/W: W for dummy write */
	nsp32_prom_write_bit(data, 0);

	/* ack */
	nsp32_prom_write_bit(data, 0);

	/* word address */
	for (i = 7; i >= 0; i--) {
		nsp32_prom_write_bit(data, ((romaddr >> i) & 1));
	}

	/* ack */
	nsp32_prom_write_bit(data, 0);

	/* start condition */
	nsp32_prom_start(data);

	/* device address */
	nsp32_prom_write_bit(data, 1);	/* 1 */
	nsp32_prom_write_bit(data, 0);	/* 0 */
	nsp32_prom_write_bit(data, 1);	/* 1 */
	nsp32_prom_write_bit(data, 0);	/* 0 */
	nsp32_prom_write_bit(data, 0);	/* A2: 0 (GND) */
	nsp32_prom_write_bit(data, 0);	/* A1: 0 (GND) */
	nsp32_prom_write_bit(data, 0);	/* A0: 0 (GND) */

	/* R/W: R */
	nsp32_prom_write_bit(data, 1);

	/* ack */
	nsp32_prom_write_bit(data, 0);

	/* data... */
	val = 0;
	for (i = 7; i >= 0; i--) {
		val += (nsp32_prom_read_bit(data) << i);
	}
	
	/* no ack */
	nsp32_prom_write_bit(data, 1);

	/* stop condition */
	nsp32_prom_stop(data);

	return val;
}