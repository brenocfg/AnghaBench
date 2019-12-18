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
struct fwtty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drain ; 
 int /*<<< orphan*/  fwtty_tx (struct fwtty_port*,int) ; 
 int /*<<< orphan*/  to_delayed_work (struct work_struct*) ; 
 struct fwtty_port* to_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwtty_drain_tx(struct work_struct *work)
{
	struct fwtty_port *port = to_port(to_delayed_work(work), drain);

	fwtty_tx(port, true);
}