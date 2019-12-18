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
typedef  int u8 ;
typedef  int u16 ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8096p_host_bus_drive(struct dib8000_state *state, u8 drive)
{
	u16 reg;

	drive &= 0x7;

	/* drive host bus 2, 3, 4 */
	reg = dib8000_read_word(state, 1798) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_write_word(state, 1798, reg);

	/* drive host bus 5,6 */
	reg = dib8000_read_word(state, 1799) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive<<8) | (drive<<2);
	dib8000_write_word(state, 1799, reg);

	/* drive host bus 7, 8, 9 */
	reg = dib8000_read_word(state, 1800) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_write_word(state, 1800, reg);

	/* drive host bus 10, 11 */
	reg = dib8000_read_word(state, 1801) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive<<8) | (drive<<2);
	dib8000_write_word(state, 1801, reg);

	/* drive host bus 12, 13, 14 */
	reg = dib8000_read_word(state, 1802) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_write_word(state, 1802, reg);
}