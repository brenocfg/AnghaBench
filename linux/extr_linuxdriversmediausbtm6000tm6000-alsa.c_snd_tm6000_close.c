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
struct tm6000_core {int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; } ;
struct snd_tm6000_card {struct tm6000_core* core; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct snd_tm6000_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_tm6000_close(struct snd_pcm_substream *substream)
{
	struct snd_tm6000_card *chip = snd_pcm_substream_chip(substream);
	struct tm6000_core *core = chip->core;

	if (atomic_read(&core->stream_started) > 0) {
		atomic_set(&core->stream_started, 0);
		schedule_work(&core->wq_trigger);
	}

	return 0;
}