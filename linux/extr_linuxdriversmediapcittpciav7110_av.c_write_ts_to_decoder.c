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
struct ipack {int dummy; } ;
struct av7110 {struct ipack* ipack; } ;

/* Variables and functions */
 int const ADAPT_FIELD ; 
 int const PAYLOAD ; 
 int const PAY_START ; 
 int const TRANS_ERROR ; 
 int /*<<< orphan*/  av7110_ipack_flush (struct ipack*) ; 
 int /*<<< orphan*/  av7110_ipack_instant_repack (int const*,size_t,struct ipack*) ; 
 int /*<<< orphan*/  av7110_ipack_reset (struct ipack*) ; 

__attribute__((used)) static int write_ts_to_decoder(struct av7110 *av7110, int type, const u8 *buf, size_t len)
{
	struct ipack *ipack = &av7110->ipack[type];

	if (buf[1] & TRANS_ERROR) {
		av7110_ipack_reset(ipack);
		return -1;
	}

	if (!(buf[3] & PAYLOAD))
		return -1;

	if (buf[1] & PAY_START)
		av7110_ipack_flush(ipack);

	if (buf[3] & ADAPT_FIELD) {
		len -= buf[4] + 1;
		buf += buf[4] + 1;
		if (!len)
			return 0;
	}

	av7110_ipack_instant_repack(buf + 4, len - 4, ipack);
	return 0;
}