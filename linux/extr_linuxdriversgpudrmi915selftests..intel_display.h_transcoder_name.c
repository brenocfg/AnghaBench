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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
#define  TRANSCODER_A 133 
#define  TRANSCODER_B 132 
#define  TRANSCODER_C 131 
#define  TRANSCODER_DSI_A 130 
#define  TRANSCODER_DSI_C 129 
#define  TRANSCODER_EDP 128 

__attribute__((used)) static inline const char *transcoder_name(enum transcoder transcoder)
{
	switch (transcoder) {
	case TRANSCODER_A:
		return "A";
	case TRANSCODER_B:
		return "B";
	case TRANSCODER_C:
		return "C";
	case TRANSCODER_EDP:
		return "EDP";
	case TRANSCODER_DSI_A:
		return "DSI A";
	case TRANSCODER_DSI_C:
		return "DSI C";
	default:
		return "<invalid>";
	}
}