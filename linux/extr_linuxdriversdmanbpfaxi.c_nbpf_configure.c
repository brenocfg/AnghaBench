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
struct nbpf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBPF_CTRL ; 
 int /*<<< orphan*/  NBPF_CTRL_LVINT ; 
 int /*<<< orphan*/  nbpf_write (struct nbpf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbpf_configure(struct nbpf_device *nbpf)
{
	nbpf_write(nbpf, NBPF_CTRL, NBPF_CTRL_LVINT);
}