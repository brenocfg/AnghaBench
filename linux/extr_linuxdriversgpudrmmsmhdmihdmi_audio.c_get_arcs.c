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
struct hdmi_msm_audio_arcs {unsigned long pixclock; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hdmi_msm_audio_arcs*) ; 
 struct hdmi_msm_audio_arcs* acr_lut ; 

__attribute__((used)) static const struct hdmi_msm_audio_arcs *get_arcs(unsigned long int pixclock)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(acr_lut); i++) {
		const struct hdmi_msm_audio_arcs *arcs = &acr_lut[i];
		if (arcs->pixclock == pixclock)
			return arcs;
	}

	return NULL;
}