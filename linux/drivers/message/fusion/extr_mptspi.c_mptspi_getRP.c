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
struct scsi_target {int dummy; } ;

/* Variables and functions */
 int MPI_SCSIDEVPAGE1_RP_DT ; 
 int MPI_SCSIDEVPAGE1_RP_HOLD_MCS ; 
 int MPI_SCSIDEVPAGE1_RP_IU ; 
 int MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK ; 
 int MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK ; 
 int MPI_SCSIDEVPAGE1_RP_PCOMP_EN ; 
 int MPI_SCSIDEVPAGE1_RP_QAS ; 
 int MPI_SCSIDEVPAGE1_RP_RD_STRM ; 
 int MPI_SCSIDEVPAGE1_RP_RTI ; 
 int MPI_SCSIDEVPAGE1_RP_SHIFT_MAX_SYNC_OFFSET ; 
 int MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD ; 
 int MPI_SCSIDEVPAGE1_RP_WIDE ; 
 int MPI_SCSIDEVPAGE1_RP_WR_FLOW ; 
 scalar_t__ spi_dt (struct scsi_target*) ; 
 scalar_t__ spi_hold_mcs (struct scsi_target*) ; 
 scalar_t__ spi_iu (struct scsi_target*) ; 
 int spi_offset (struct scsi_target*) ; 
 scalar_t__ spi_pcomp_en (struct scsi_target*) ; 
 int spi_period (struct scsi_target*) ; 
 scalar_t__ spi_qas (struct scsi_target*) ; 
 scalar_t__ spi_rd_strm (struct scsi_target*) ; 
 scalar_t__ spi_rti (struct scsi_target*) ; 
 scalar_t__ spi_width (struct scsi_target*) ; 
 scalar_t__ spi_wr_flow (struct scsi_target*) ; 

__attribute__((used)) static u32 mptspi_getRP(struct scsi_target *starget)
{
	u32 nego = 0;

	nego |= spi_iu(starget) ? MPI_SCSIDEVPAGE1_RP_IU : 0;
	nego |= spi_dt(starget) ? MPI_SCSIDEVPAGE1_RP_DT : 0;
	nego |= spi_qas(starget) ? MPI_SCSIDEVPAGE1_RP_QAS : 0;
	nego |= spi_hold_mcs(starget) ? MPI_SCSIDEVPAGE1_RP_HOLD_MCS : 0;
	nego |= spi_wr_flow(starget) ? MPI_SCSIDEVPAGE1_RP_WR_FLOW : 0;
	nego |= spi_rd_strm(starget) ? MPI_SCSIDEVPAGE1_RP_RD_STRM : 0;
	nego |= spi_rti(starget) ? MPI_SCSIDEVPAGE1_RP_RTI : 0;
	nego |= spi_pcomp_en(starget) ? MPI_SCSIDEVPAGE1_RP_PCOMP_EN : 0;

	nego |= (spi_period(starget) <<  MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD) & MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK;
	nego |= (spi_offset(starget) << MPI_SCSIDEVPAGE1_RP_SHIFT_MAX_SYNC_OFFSET) & MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK;
	nego |= spi_width(starget) ?  MPI_SCSIDEVPAGE1_RP_WIDE : 0;

	return nego;
}