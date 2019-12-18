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
struct csio_lnode {int dummy; } ;
typedef  scalar_t__ csio_sm_state_t ;

/* Variables and functions */
 scalar_t__ csio_get_state (struct csio_lnode*) ; 
 scalar_t__ csio_lns_ready ; 

int
csio_is_lnode_ready(struct csio_lnode *ln)
{
	return (csio_get_state(ln) == ((csio_sm_state_t)csio_lns_ready));
}