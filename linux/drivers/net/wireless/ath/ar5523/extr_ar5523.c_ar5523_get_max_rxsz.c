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
struct ar5523 {int /*<<< orphan*/  rxbufsz; } ;
typedef  int /*<<< orphan*/  rxsize ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_SANE_RXBUFSZ ; 
 int /*<<< orphan*/  ST_WDC_TRANSPORT_CHUNK_SIZE ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,...) ; 
 int ar5523_get_status (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_get_max_rxsz(struct ar5523 *ar)
{
	int error;
	__be32 rxsize;

	/* Get max rx size */
	error = ar5523_get_status(ar, ST_WDC_TRANSPORT_CHUNK_SIZE, &rxsize,
				  sizeof(rxsize));
	if (error != 0) {
		ar5523_err(ar, "could not read max RX size\n");
		return error;
	}

	ar->rxbufsz = be32_to_cpu(rxsize);

	if (!ar->rxbufsz || ar->rxbufsz > AR5523_SANE_RXBUFSZ) {
		ar5523_err(ar, "Bad rxbufsz from device. Using %d instead\n",
			   AR5523_SANE_RXBUFSZ);
		ar->rxbufsz = AR5523_SANE_RXBUFSZ;
	}

	ar5523_dbg(ar, "Max RX buf size: %d\n", ar->rxbufsz);
	return 0;
}