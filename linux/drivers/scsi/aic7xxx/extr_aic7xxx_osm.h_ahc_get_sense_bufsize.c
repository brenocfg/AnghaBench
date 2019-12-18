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
typedef  int uint32_t ;
struct scsi_sense_data {int dummy; } ;
struct scb {int dummy; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
ahc_get_sense_bufsize(struct ahc_softc *ahc, struct scb *scb)
{
	return (sizeof(struct scsi_sense_data));
}