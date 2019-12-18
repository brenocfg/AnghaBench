#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct hva_dev* private; } ;
struct hva_ctx {int flags; } ;
struct TYPE_2__ {struct hva_ctx last_ctx; } ;
struct hva_dev {TYPE_1__ dbg; } ;

/* Variables and functions */
 int HVA_FLAG_STREAMINFO ; 
 int /*<<< orphan*/  format_ctx (struct seq_file*,struct hva_ctx*) ; 
 int /*<<< orphan*/  hva_dbg_perf_compute (struct hva_ctx*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int last_show(struct seq_file *s, void *data)
{
	struct hva_dev *hva = s->private;
	struct hva_ctx *last_ctx = &hva->dbg.last_ctx;

	if (last_ctx->flags & HVA_FLAG_STREAMINFO) {
		seq_puts(s, "[last encoding]\n");

		hva_dbg_perf_compute(last_ctx);
		format_ctx(s, last_ctx);
	} else {
		seq_puts(s, "[no information recorded about last encoding]\n");
	}

	return 0;
}