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
typedef  int u32 ;

/* Variables and functions */
#define  BIDIRECTIONAL 130 
 int DIRECTIONAL_MSK ; 
#define  INPUT_ONLY 129 
#define  OUTPUT_ONLY 128 

__attribute__((used)) static char *get_dma_direction(u32 status)
{
	switch (status & DIRECTIONAL_MSK) {
	case INPUT_ONLY: return "Input";
	case OUTPUT_ONLY: return "Output";
	case BIDIRECTIONAL: return "Bidirectional";
	}
	return "";
}