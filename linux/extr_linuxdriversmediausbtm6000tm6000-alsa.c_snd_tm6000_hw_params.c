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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int dsp_buffer_alloc (struct snd_pcm_substream*,int) ; 
 int params_period_bytes (struct snd_pcm_hw_params*) ; 
 int params_periods (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int snd_tm6000_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *hw_params)
{
	int size, rc;

	size = params_period_bytes(hw_params) * params_periods(hw_params);

	rc = dsp_buffer_alloc(substream, size);
	if (rc < 0)
		return rc;

	return 0;
}