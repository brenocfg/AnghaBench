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
struct nvidia_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvGetClocks (struct nvidia_par*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void nv30UpdateArbitrationSettings (
    struct nvidia_par *par,
    unsigned int      *burst,
    unsigned int      *lwm
)
{
    unsigned int MClk, NVClk;
    unsigned int fifo_size, burst_size, graphics_lwm;

    fifo_size = 2048;
    burst_size = 512;
    graphics_lwm = fifo_size - burst_size;

    nvGetClocks(par, &MClk, &NVClk);

    *burst = 0;
    burst_size >>= 5;
    while(burst_size >>= 1) (*burst)++;
    *lwm = graphics_lwm >> 3;
}