#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pcx; int /*<<< orphan*/  length; int /*<<< orphan*/  fsize; int /*<<< orphan*/  ldflg; } ;
struct TYPE_4__ {TYPE_1__ ftp; } ;
struct sclp_diag_evbuf {scalar_t__ route; TYPE_2__ mdd; } ;
struct evbuf_header {scalar_t__ type; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ EVTYP_DIAG_TEST ; 
 scalar_t__ SCLP_DIAG_FTP_EVBUF_LEN ; 
 scalar_t__ SCLP_DIAG_FTP_ROUTE ; 
 scalar_t__ SCLP_DIAG_FTP_XPCX ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct evbuf_header*,int,struct evbuf_header*) ; 
 int /*<<< orphan*/  sclp_ftp_fsize ; 
 int /*<<< orphan*/  sclp_ftp_ldflg ; 
 int /*<<< orphan*/  sclp_ftp_length ; 
 int /*<<< orphan*/  sclp_ftp_rx_complete ; 

__attribute__((used)) static void sclp_ftp_rxcb(struct evbuf_header *evbuf)
{
	struct sclp_diag_evbuf *diag = (struct sclp_diag_evbuf *) evbuf;

	/*
	 * Check for Diagnostic Test FTP Service
	 */
	if (evbuf->type != EVTYP_DIAG_TEST ||
	    diag->route != SCLP_DIAG_FTP_ROUTE ||
	    diag->mdd.ftp.pcx != SCLP_DIAG_FTP_XPCX ||
	    evbuf->length < SCLP_DIAG_FTP_EVBUF_LEN)
		return;

#ifdef DEBUG
	pr_debug("SCLP (ET7) RX-IRQ, Event @ 0x%p: %*phN\n",
		 evbuf, 24, evbuf);
#endif

	/*
	 * Because the event buffer is located in a page which is owned
	 * by the SCLP core, all data of interest must be copied. The
	 * error indication is in 'sclp_ftp_ldflg'
	 */
	sclp_ftp_ldflg = diag->mdd.ftp.ldflg;
	sclp_ftp_fsize = diag->mdd.ftp.fsize;
	sclp_ftp_length = diag->mdd.ftp.length;

	complete(&sclp_ftp_rx_complete);
}