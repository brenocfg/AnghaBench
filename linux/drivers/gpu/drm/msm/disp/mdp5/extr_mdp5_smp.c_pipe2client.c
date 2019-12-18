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
typedef  scalar_t__ u32 ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;
struct TYPE_3__ {scalar_t__* clients; } ;
struct TYPE_4__ {TYPE_1__ smp; } ;

/* Variables and functions */
 scalar_t__ CID_UNUSED ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_2__* mdp5_cfg ; 
 int pipe2nclients (int) ; 

__attribute__((used)) static inline u32 pipe2client(enum mdp5_pipe pipe, int plane)
{
#define CID_UNUSED	0

	if (WARN_ON(plane >= pipe2nclients(pipe)))
		return CID_UNUSED;

	/*
	 * Note on SMP clients:
	 * For ViG pipes, fetch Y/Cr/Cb-components clients are always
	 * consecutive, and in that order.
	 *
	 * e.g.:
	 * if mdp5_cfg->smp.clients[SSPP_VIG0] = N,
	 *	Y  plane's client ID is N
	 *	Cr plane's client ID is N + 1
	 *	Cb plane's client ID is N + 2
	 */

	return mdp5_cfg->smp.clients[pipe] + plane;
}