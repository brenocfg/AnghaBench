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
struct wil6210_priv {TYPE_1__* srings; } ;
struct seq_file {struct wil6210_priv* private; } ;
struct TYPE_2__ {scalar_t__ va; } ;

/* Variables and functions */
 int WIL6210_MAX_STATUS_RINGS ; 
 int /*<<< orphan*/  wil_print_sring (struct seq_file*,struct wil6210_priv*,TYPE_1__*) ; 

__attribute__((used)) static int srings_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	int i = 0;

	for (i = 0; i < WIL6210_MAX_STATUS_RINGS; i++)
		if (wil->srings[i].va)
			wil_print_sring(s, wil, &wil->srings[i]);

	return 0;
}