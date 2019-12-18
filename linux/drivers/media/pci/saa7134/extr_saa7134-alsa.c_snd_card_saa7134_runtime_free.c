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
struct snd_pcm_runtime {int /*<<< orphan*/ * private_data; } ;
typedef  int /*<<< orphan*/  snd_card_saa7134_pcm_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_card_saa7134_runtime_free(struct snd_pcm_runtime *runtime)
{
	snd_card_saa7134_pcm_t *pcm = runtime->private_data;

	kfree(pcm);
}