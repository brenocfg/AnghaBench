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
struct work_struct {int dummy; } ;
struct fwtty_peer {int /*<<< orphan*/  (* workfn ) (struct work_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct work_struct*) ; 
 struct fwtty_peer* to_peer (struct work_struct*,struct work_struct*) ; 

__attribute__((used)) static void fwserial_peer_workfn(struct work_struct *work)
{
	struct fwtty_peer *peer = to_peer(work, work);

	peer->workfn(work);
}