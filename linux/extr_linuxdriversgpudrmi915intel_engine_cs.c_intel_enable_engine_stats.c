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
struct intel_engine_execlists {struct execlist_port* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled_at; int /*<<< orphan*/  start; scalar_t__ active; int /*<<< orphan*/  enabled; } ;
struct intel_engine_cs {TYPE_2__ timeline; TYPE_1__ stats; struct intel_engine_execlists execlists; } ;
struct execlist_port {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 unsigned int execlists_num_ports (struct intel_engine_execlists*) ; 
 int /*<<< orphan*/  intel_engine_supports_stats (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ port_isset (struct execlist_port const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

int intel_enable_engine_stats(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists *execlists = &engine->execlists;
	unsigned long flags;
	int err = 0;

	if (!intel_engine_supports_stats(engine))
		return -ENODEV;

	spin_lock_irqsave(&engine->timeline.lock, flags);
	write_seqlock(&engine->stats.lock);

	if (unlikely(engine->stats.enabled == ~0)) {
		err = -EBUSY;
		goto unlock;
	}

	if (engine->stats.enabled++ == 0) {
		const struct execlist_port *port = execlists->port;
		unsigned int num_ports = execlists_num_ports(execlists);

		engine->stats.enabled_at = ktime_get();

		/* XXX submission method oblivious? */
		while (num_ports-- && port_isset(port)) {
			engine->stats.active++;
			port++;
		}

		if (engine->stats.active)
			engine->stats.start = engine->stats.enabled_at;
	}

unlock:
	write_sequnlock(&engine->stats.lock);
	spin_unlock_irqrestore(&engine->timeline.lock, flags);

	return err;
}