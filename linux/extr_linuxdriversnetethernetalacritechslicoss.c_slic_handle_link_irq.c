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
struct slic_shmem_data {int /*<<< orphan*/  link; } ;
struct slic_shmem {struct slic_shmem_data* shmem_data; } ;
struct slic_device {struct slic_shmem shmem; } ;

/* Variables and functions */
 unsigned int DUPLEX_FULL ; 
 unsigned int DUPLEX_HALF ; 
 unsigned int DUPLEX_UNKNOWN ; 
 int SLIC_GIG_FULLDUPLEX ; 
 int SLIC_GIG_LINKUP ; 
 int SLIC_GIG_SPEED_100 ; 
 int SLIC_GIG_SPEED_1000 ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_UNKNOWN ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_configure_link (struct slic_device*,int,unsigned int) ; 

__attribute__((used)) static void slic_handle_link_irq(struct slic_device *sdev)
{
	struct slic_shmem *sm = &sdev->shmem;
	struct slic_shmem_data *sm_data = sm->shmem_data;
	unsigned int duplex;
	int speed;
	u32 link;

	link = le32_to_cpu(sm_data->link);

	if (link & SLIC_GIG_LINKUP) {
		if (link & SLIC_GIG_SPEED_1000)
			speed = SPEED_1000;
		else if (link & SLIC_GIG_SPEED_100)
			speed = SPEED_100;
		else
			speed = SPEED_10;

		duplex = (link & SLIC_GIG_FULLDUPLEX) ? DUPLEX_FULL :
							DUPLEX_HALF;
	} else {
		duplex = DUPLEX_UNKNOWN;
		speed = SPEED_UNKNOWN;
	}
	slic_configure_link(sdev, speed, duplex);
}