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
struct saa7146_standard {int dummy; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int std_callback(struct saa7146_dev *dev, struct saa7146_standard *std)
{
	return 0;
}