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
struct platform_device {int dummy; } ;
struct mlxbf_tmfifo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxbf_tmfifo_cleanup (struct mlxbf_tmfifo*) ; 
 struct mlxbf_tmfifo* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mlxbf_tmfifo_remove(struct platform_device *pdev)
{
	struct mlxbf_tmfifo *fifo = platform_get_drvdata(pdev);

	mlxbf_tmfifo_cleanup(fifo);

	return 0;
}