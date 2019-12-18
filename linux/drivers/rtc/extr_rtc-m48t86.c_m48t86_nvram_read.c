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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T86_NVRAM (unsigned int) ; 
 int /*<<< orphan*/  m48t86_readb (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m48t86_nvram_read(void *priv, unsigned int off, void *buf,
			     size_t count)
{
	struct device *dev = priv;
	unsigned int i;

	for (i = 0; i < count; i++)
		((u8 *)buf)[i] = m48t86_readb(dev, M48T86_NVRAM(off + i));

	return 0;
}