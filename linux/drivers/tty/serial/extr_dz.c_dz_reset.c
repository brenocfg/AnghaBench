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
struct dz_port {struct dz_mux* mux; } ;
struct dz_mux {int initialised; } ;

/* Variables and functions */
 int DZ_CLR ; 
 int /*<<< orphan*/  DZ_CSR ; 
 int DZ_MSE ; 
 int dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iob () ; 

__attribute__((used)) static void dz_reset(struct dz_port *dport)
{
	struct dz_mux *mux = dport->mux;

	if (mux->initialised)
		return;

	dz_out(dport, DZ_CSR, DZ_CLR);
	while (dz_in(dport, DZ_CSR) & DZ_CLR);
	iob();

	/* Enable scanning.  */
	dz_out(dport, DZ_CSR, DZ_MSE);

	mux->initialised = 1;
}