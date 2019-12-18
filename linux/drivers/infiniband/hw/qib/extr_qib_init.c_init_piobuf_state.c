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
typedef  int u32 ;
struct qib_devdata {int num_pports; int cfgctxts; int first_user_ctxt; int pbufsctxt; int pioavregs; int /*<<< orphan*/  (* f_initvl15_bufs ) (struct qib_devdata*) ;scalar_t__ piobcnt4k; scalar_t__ piobcnt2k; scalar_t__* pioavailshadow; int /*<<< orphan*/ * pioavailregs_dma; scalar_t__ lastctxt_piobuf; scalar_t__ ctxts_extrabuf; scalar_t__ pport; int /*<<< orphan*/  (* f_sendctrl ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  QIB_SENDCTRL_DISARM_ALL ; 
 int /*<<< orphan*/  QIB_SENDCTRL_FLUSH ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_KERN ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_chg_pioavailkernel (struct qib_devdata*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct qib_devdata*) ; 

__attribute__((used)) static void init_piobuf_state(struct qib_devdata *dd)
{
	int i, pidx;
	u32 uctxts;

	/*
	 * Ensure all buffers are free, and fifos empty.  Buffers
	 * are common, so only do once for port 0.
	 *
	 * After enable and qib_chg_pioavailkernel so we can safely
	 * enable pioavail updates and PIOENABLE.  After this, packets
	 * are ready and able to go out.
	 */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_ALL);
	for (pidx = 0; pidx < dd->num_pports; ++pidx)
		dd->f_sendctrl(dd->pport + pidx, QIB_SENDCTRL_FLUSH);

	/*
	 * If not all sendbufs are used, add the one to each of the lower
	 * numbered contexts.  pbufsctxt and lastctxt_piobuf are
	 * calculated in chip-specific code because it may cause some
	 * chip-specific adjustments to be made.
	 */
	uctxts = dd->cfgctxts - dd->first_user_ctxt;
	dd->ctxts_extrabuf = dd->pbufsctxt ?
		dd->lastctxt_piobuf - (dd->pbufsctxt * uctxts) : 0;

	/*
	 * Set up the shadow copies of the piobufavail registers,
	 * which we compare against the chip registers for now, and
	 * the in memory DMA'ed copies of the registers.
	 * By now pioavail updates to memory should have occurred, so
	 * copy them into our working/shadow registers; this is in
	 * case something went wrong with abort, but mostly to get the
	 * initial values of the generation bit correct.
	 */
	for (i = 0; i < dd->pioavregs; i++) {
		__le64 tmp;

		tmp = dd->pioavailregs_dma[i];
		/*
		 * Don't need to worry about pioavailkernel here
		 * because we will call qib_chg_pioavailkernel() later
		 * in initialization, to busy out buffers as needed.
		 */
		dd->pioavailshadow[i] = le64_to_cpu(tmp);
	}
	while (i < ARRAY_SIZE(dd->pioavailshadow))
		dd->pioavailshadow[i++] = 0; /* for debugging sanity */

	/* after pioavailshadow is setup */
	qib_chg_pioavailkernel(dd, 0, dd->piobcnt2k + dd->piobcnt4k,
			       TXCHK_CHG_TYPE_KERN, NULL);
	dd->f_initvl15_bufs(dd);
}