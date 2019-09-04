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
typedef  int /*<<< orphan*/  word ;
struct sbefifo {int /*<<< orphan*/  fsi_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SBEFIFO_UP ; 
 int fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sbefifo_up_write(struct sbefifo *sbefifo, __be32 word)
{
	return fsi_device_write(sbefifo->fsi_dev, SBEFIFO_UP, &word,
				sizeof(word));
}