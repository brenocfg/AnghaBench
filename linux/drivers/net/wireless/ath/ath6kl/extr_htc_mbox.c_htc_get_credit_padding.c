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
struct htc_endpoint {int conn_flags; } ;

/* Variables and functions */
 int HTC_FLGS_TX_BNDL_PAD_EN ; 

__attribute__((used)) static int htc_get_credit_padding(unsigned int cred_sz, int *len,
				  struct htc_endpoint *ep)
{
	int rem_cred, cred_pad;

	rem_cred = *len % cred_sz;

	/* No padding needed */
	if  (!rem_cred)
		return 0;

	if (!(ep->conn_flags & HTC_FLGS_TX_BNDL_PAD_EN))
		return -1;

	/*
	 * The transfer consumes a "partial" credit, this
	 * packet cannot be bundled unless we add
	 * additional "dummy" padding (max 255 bytes) to
	 * consume the entire credit.
	 */
	cred_pad = *len < cred_sz ? (cred_sz - *len) : rem_cred;

	if ((cred_pad > 0) && (cred_pad <= 255))
		*len += cred_pad;
	else
		/* The amount of padding is too large, send as non-bundled */
		return -1;

	return cred_pad;
}