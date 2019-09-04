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
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ chan; } ;
struct idma64_chan {TYPE_2__ vchan; } ;
struct idma64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idma64_chan_stop (struct idma64*,struct idma64_chan*) ; 
 struct idma64* to_idma64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_stop_transfer(struct idma64_chan *idma64c)
{
	struct idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);

	idma64_chan_stop(idma64, idma64c);
}