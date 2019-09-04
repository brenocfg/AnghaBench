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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int PROG_CHUNK ; 
 int qib_sd7220_ram_xfer (struct qib_devdata*,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_sd7220_prog_ld(struct qib_devdata *dd, int sdnum,
			      const u8 *img, int len, int offset)
{
	int cnt, sofar, req;

	sofar = 0;
	while (sofar < len) {
		req = len - sofar;
		if (req > PROG_CHUNK)
			req = PROG_CHUNK;
		cnt = qib_sd7220_ram_xfer(dd, sdnum, offset + sofar,
					  (u8 *)img + sofar, req, 0);
		if (cnt < req) {
			sofar = -1;
			break;
		}
		sofar += req;
	}
	return sofar;
}