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
struct sd {int /*<<< orphan*/  avg_lum; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_lum(struct sd *sd,
		    u8 *data)
{
	int avg_lum;

	/*	w0 w1 w2
	 *	w3 w4 w5
	 *	w6 w7 w8
	 */
	avg_lum = (data[27] << 8) + data[28]		/* w3 */

		+ (data[31] << 8) + data[32]		/* w5 */

		+ (data[23] << 8) + data[24]		/* w1 */

		+ (data[35] << 8) + data[36]		/* w7 */

		+ (data[29] << 10) + (data[30] << 2);	/* w4 * 4 */
	avg_lum >>= 10;
	atomic_set(&sd->avg_lum, avg_lum);
}