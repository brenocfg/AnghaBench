#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spk_synth {scalar_t__ alive; int /*<<< orphan*/  long_name; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* write ) (TYPE_2__*,char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speakup_start_ttys () ; 
 TYPE_2__* speakup_tty ; 
 int /*<<< orphan*/  speakup_tty_mutex ; 
 int stub1 (TYPE_2__*,char const*,int) ; 

__attribute__((used)) static int spk_ttyio_out(struct spk_synth *in_synth, const char ch)
{
	mutex_lock(&speakup_tty_mutex);
	if (in_synth->alive && speakup_tty && speakup_tty->ops->write) {
		int ret = speakup_tty->ops->write(speakup_tty, &ch, 1);

		mutex_unlock(&speakup_tty_mutex);
		if (ret == 0)
			/* No room */
			return 0;
		if (ret < 0) {
			pr_warn("%s: I/O error, deactivating speakup\n",
				in_synth->long_name);
			/* No synth any more, so nobody will restart TTYs,
			 * and we thus need to do it ourselves.  Now that there
			 * is no synth we can let application flood anyway
			 */
			in_synth->alive = 0;
			speakup_start_ttys();
			return 0;
		}
		return 1;
	}

	mutex_unlock(&speakup_tty_mutex);
	return 0;
}