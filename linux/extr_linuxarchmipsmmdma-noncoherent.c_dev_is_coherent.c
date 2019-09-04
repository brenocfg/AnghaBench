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
struct device {int dummy; } ;

/* Variables and functions */
#define  IO_COHERENCE_DEFAULT 130 
#define  IO_COHERENCE_DISABLED 129 
#define  IO_COHERENCE_ENABLED 128 
 int coherentio ; 
 int hw_coherentio ; 

__attribute__((used)) static inline int dev_is_coherent(struct device *dev)
{
	switch (coherentio) {
	default:
	case IO_COHERENCE_DEFAULT:
		return hw_coherentio;
	case IO_COHERENCE_ENABLED:
		return 1;
	case IO_COHERENCE_DISABLED:
		return 0;
	}
}